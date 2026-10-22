---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 16:56:16 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1792702060 52
1792702065 52
1792702070 52
1792702075 52
1792702080 52
1792702085 52
1792702090 52
1792702095 52
1792702100 54
1792702105 54
1792702110 54
1792702115 54
1792702120 54
1792702125 54
1792702130 54
1792702135 54
1792702140 54
1792702145 54
1792702150 54
1792702155 54
```
</details>

---

