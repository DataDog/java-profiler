---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 12:22:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 11 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792426628 43
1792426633 43
1792426638 48
1792426643 48
1792426648 48
1792426653 48
1792426658 48
1792426663 48
1792426668 48
1792426673 48
1792426678 48
1792426683 48
1792426688 48
1792426693 48
1792426698 48
1792426703 48
1792426708 48
1792426713 48
1792426718 48
1792426723 48
```
</details>

---

