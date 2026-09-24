---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 15:41:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790278663 64
1790278668 64
1790278673 64
1790278678 64
1790278683 64
1790278688 64
1790278693 64
1790278698 64
1790278703 64
1790278708 64
1790278713 64
1790278718 64
1790278723 64
1790278728 64
1790278733 64
1790278738 64
1790278743 64
1790278748 64
1790278753 64
1790278758 64
```
</details>

---

