---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-01 12:28:07 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (5 unique values: 56-60 cores)</summary>

```
1788279732 59
1788279737 59
1788279742 59
1788279747 59
1788279752 59
1788279757 59
1788279762 59
1788279767 59
1788279772 59
1788279778 59
1788279783 59
1788279788 59
1788279793 59
1788279798 59
1788279803 59
1788279808 59
1788279813 60
1788279818 60
1788279823 58
1788279828 58
```
</details>

---

