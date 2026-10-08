---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:53:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1791470853 61
1791470858 61
1791470863 61
1791470868 61
1791470873 61
1791470878 61
1791470883 61
1791470888 61
1791470893 61
1791470898 63
1791470903 63
1791470908 63
1791470913 63
1791470918 63
1791470923 63
1791470928 63
1791470933 63
1791470938 63
1791470943 63
1791470948 63
```
</details>

---

