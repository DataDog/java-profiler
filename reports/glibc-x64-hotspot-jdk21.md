---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 08:50:42 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 11-13 cores)</summary>

```
1773232923 11
1773232928 11
1773232933 11
1773232938 11
1773232943 11
1773232948 11
1773232953 11
1773232958 13
1773232963 13
1773232968 13
1773232973 13
1773232978 13
1773232983 13
1773232988 13
1773232993 13
1773232998 13
1773233003 13
1773233008 13
1773233013 13
1773233018 13
```
</details>

---

