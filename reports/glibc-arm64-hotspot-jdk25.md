---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:15:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 37 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1789743653 23
1789743658 23
1789743663 23
1789743668 23
1789743673 23
1789743678 33
1789743683 33
1789743688 23
1789743693 23
1789743698 23
1789743703 23
1789743708 29
1789743713 29
1789743718 29
1789743723 29
1789743728 29
1789743733 29
1789743738 29
1789743743 29
1789743748 29
```
</details>

---

