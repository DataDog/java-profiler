---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:15:15 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (5 unique values: 39-59 cores)</summary>

```
1789743639 39
1789743644 43
1789743649 43
1789743654 53
1789743659 53
1789743664 53
1789743669 53
1789743674 58
1789743679 58
1789743684 58
1789743689 58
1789743694 58
1789743699 59
1789743704 59
1789743709 59
1789743714 59
1789743719 59
1789743724 59
1789743729 59
1789743734 59
```
</details>

---

