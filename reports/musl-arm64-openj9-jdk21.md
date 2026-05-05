---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-05 06:30:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777976670 64
1777976675 64
1777976680 64
1777976685 64
1777976690 64
1777976695 64
1777976700 64
1777976705 64
1777976710 64
1777976715 64
1777976720 64
1777976725 64
1777976730 64
1777976735 64
1777976740 64
1777976745 64
1777976750 64
1777976755 64
1777976760 64
1777976765 64
```
</details>

---

