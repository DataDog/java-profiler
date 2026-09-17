---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:15:40 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1789686658 30
1789686663 30
1789686668 30
1789686673 30
1789686678 30
1789686683 30
1789686688 30
1789686693 30
1789686698 30
1789686703 30
1789686708 30
1789686713 30
1789686718 30
1789686723 30
1789686728 30
1789686733 30
1789686738 30
1789686743 30
1789686748 30
1789686753 30
```
</details>

---

