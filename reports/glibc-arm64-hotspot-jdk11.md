---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:59:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795200952 50
1795200957 50
1795200962 50
1795200967 50
1795200972 50
1795200977 50
1795200982 50
1795200987 50
1795200992 50
1795200997 50
1795201002 50
1795201007 50
1795201012 50
1795201017 50
1795201022 50
1795201027 50
1795201032 50
1795201037 50
1795201042 50
1795201047 50
```
</details>

---

