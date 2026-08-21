---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 03:04:24 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 11 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (3 unique values: 22-34 cores)</summary>

```
1787295617 22
1787295622 22
1787295627 22
1787295632 22
1787295638 22
1787295643 22
1787295648 22
1787295653 22
1787295658 22
1787295663 22
1787295668 22
1787295673 22
1787295678 34
1787295683 34
1787295688 34
1787295693 34
1787295698 34
1787295703 34
1787295708 34
1787295713 34
```
</details>

---

