---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:18:06 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (4 unique values: 16-34 cores)</summary>

```
1790766817 34
1790766822 34
1790766827 25
1790766832 25
1790766837 16
1790766842 16
1790766847 16
1790766852 16
1790766857 16
1790766862 16
1790766867 16
1790766872 16
1790766877 21
1790766882 21
1790766887 21
1790766892 21
1790766897 21
1790766902 21
1790766907 21
1790766912 21
```
</details>

---

