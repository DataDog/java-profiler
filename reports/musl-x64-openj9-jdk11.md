---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 07:44:49 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 976 |
| Sample Rate | 16.27/sec |
| Health Score | 1017% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 66-76 cores)</summary>

```
1791545928 73
1791545933 73
1791545938 73
1791545943 73
1791545948 73
1791545953 73
1791545958 76
1791545963 76
1791545968 76
1791545973 76
1791545978 76
1791545983 76
1791545988 76
1791545993 76
1791545998 76
1791546003 76
1791546008 76
1791546013 76
1791546018 68
1791546023 68
```
</details>

---

