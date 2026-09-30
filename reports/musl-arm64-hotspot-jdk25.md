---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 11:45:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 12 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (4 unique values: 47-59 cores)</summary>

```
1790782797 53
1790782802 53
1790782807 53
1790782812 48
1790782817 48
1790782822 48
1790782827 48
1790782832 48
1790782837 48
1790782842 59
1790782847 59
1790782852 59
1790782857 59
1790782862 59
1790782867 59
1790782872 59
1790782877 59
1790782882 47
1790782887 47
1790782892 47
```
</details>

---

