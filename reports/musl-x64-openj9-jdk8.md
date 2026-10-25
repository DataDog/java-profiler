---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-25 08:54:36 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 59-94 cores)</summary>

```
1792932501 61
1792932506 61
1792932511 61
1792932516 61
1792932521 61
1792932526 61
1792932531 59
1792932536 59
1792932541 59
1792932546 59
1792932551 59
1792932556 59
1792932561 61
1792932566 61
1792932571 61
1792932576 61
1792932581 61
1792932586 61
1792932591 61
1792932596 61
```
</details>

---

