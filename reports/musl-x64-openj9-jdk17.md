---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 85-94 cores)</summary>

```
1793621903 87
1793621908 85
1793621913 85
1793621918 85
1793621923 85
1793621928 94
1793621933 94
1793621938 94
1793621943 94
1793621948 94
1793621953 94
1793621958 94
1793621963 94
1793621968 94
1793621973 94
1793621978 94
1793621983 94
1793621988 94
1793621993 94
1793621998 94
```
</details>

---

