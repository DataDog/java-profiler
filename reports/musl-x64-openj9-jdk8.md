---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-25 00:58:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 74-92 cores)</summary>

```
1790312051 76
1790312056 76
1790312061 76
1790312066 76
1790312071 76
1790312076 76
1790312081 76
1790312086 76
1790312091 74
1790312096 74
1790312101 82
1790312106 82
1790312111 82
1790312116 82
1790312121 78
1790312126 78
1790312131 78
1790312136 86
1790312141 86
1790312146 88
```
</details>

---

