---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 07:28:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 12 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 12 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1790248689 46
1790248694 46
1790248699 46
1790248704 48
1790248709 48
1790248714 48
1790248719 48
1790248724 48
1790248729 47
1790248734 47
1790248739 47
1790248744 47
1790248749 47
1790248754 47
1790248759 46
1790248764 46
1790248769 46
1790248774 46
1790248779 46
1790248784 46
```
</details>

---

