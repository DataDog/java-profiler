---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:12:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1777558036 81
1777558041 81
1777558046 81
1777558051 79
1777558056 79
1777558061 79
1777558066 81
1777558071 81
1777558076 81
1777558081 81
1777558086 81
1777558091 81
1777558096 81
1777558101 81
1777558106 81
1777558111 81
1777558116 81
1777558121 81
1777558126 81
1777558131 81
```
</details>

---

