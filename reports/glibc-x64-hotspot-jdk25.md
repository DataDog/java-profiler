---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:53:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 54-82 cores)</summary>

```
1791470853 82
1791470858 82
1791470863 82
1791470868 82
1791470873 82
1791470878 82
1791470883 82
1791470888 82
1791470893 82
1791470898 82
1791470903 82
1791470908 58
1791470913 58
1791470918 58
1791470923 58
1791470928 58
1791470933 58
1791470938 54
1791470943 54
1791470948 54
```
</details>

---

