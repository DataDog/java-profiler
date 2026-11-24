---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:18:53 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 11 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795529682 28
1795529687 28
1795529692 28
1795529697 28
1795529702 28
1795529707 28
1795529712 28
1795529717 28
1795529722 28
1795529727 28
1795529732 33
1795529737 33
1795529742 33
1795529747 33
1795529752 33
1795529757 33
1795529762 33
1795529767 33
1795529772 33
1795529777 33
```
</details>

---

