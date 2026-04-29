---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-29 11:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 82-93 cores)</summary>

```
1777475062 82
1777475067 91
1777475072 91
1777475077 93
1777475082 93
1777475087 93
1777475092 93
1777475097 93
1777475102 93
1777475107 93
1777475112 93
1777475117 93
1777475122 93
1777475127 93
1777475132 93
1777475137 92
1777475142 92
1777475147 92
1777475152 92
1777475157 92
```
</details>

---

