---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 12:30:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 8 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790785496 43
1790785501 43
1790785506 43
1790785511 43
1790785516 43
1790785521 43
1790785526 43
1790785531 43
1790785536 43
1790785541 43
1790785546 43
1790785551 43
1790785556 48
1790785561 48
1790785566 48
1790785571 48
1790785576 48
1790785581 48
1790785586 48
1790785591 48
```
</details>

---

