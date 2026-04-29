---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1777475047 60
1777475052 60
1777475057 60
1777475062 60
1777475067 60
1777475072 55
1777475077 55
1777475082 55
1777475087 55
1777475092 55
1777475097 55
1777475102 60
1777475107 60
1777475112 60
1777475117 55
1777475122 55
1777475127 55
1777475132 55
1777475137 55
1777475142 55
```
</details>

---

