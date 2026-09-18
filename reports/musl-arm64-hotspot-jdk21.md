---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:15:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789743653 47
1789743658 47
1789743663 47
1789743668 47
1789743673 47
1789743678 47
1789743683 47
1789743688 47
1789743693 47
1789743698 47
1789743703 47
1789743708 47
1789743713 47
1789743718 47
1789743723 47
1789743728 47
1789743733 47
1789743738 47
1789743743 47
1789743748 47
```
</details>

---

