---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 09:12:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (5 unique values: 51-76 cores)</summary>

```
1792156061 51
1792156066 51
1792156071 51
1792156076 51
1792156081 51
1792156086 51
1792156091 51
1792156096 56
1792156101 56
1792156106 76
1792156111 76
1792156116 55
1792156121 55
1792156126 55
1792156131 55
1792156136 55
1792156141 55
1792156146 55
1792156151 75
1792156156 75
```
</details>

---

