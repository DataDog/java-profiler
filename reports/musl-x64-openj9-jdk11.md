---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 06:49:23 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 50-81 cores)</summary>

```
1790332964 50
1790332969 50
1790332974 50
1790332979 50
1790332984 50
1790332989 50
1790332994 50
1790332999 50
1790333004 50
1790333009 50
1790333014 71
1790333019 71
1790333024 71
1790333029 71
1790333034 71
1790333039 71
1790333044 71
1790333049 71
1790333054 71
1790333059 71
```
</details>

---

