---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 10:11:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792505024 51
1792505029 51
1792505034 51
1792505039 51
1792505044 51
1792505049 51
1792505055 51
1792505060 51
1792505065 51
1792505070 51
1792505075 51
1792505080 51
1792505085 51
1792505090 51
1792505095 51
1792505100 51
1792505105 51
1792505110 51
1792505115 51
1792505120 46
```
</details>

---

