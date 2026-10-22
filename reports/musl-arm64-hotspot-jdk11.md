---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:39:25 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792686801 43
1792686806 43
1792686811 43
1792686816 43
1792686821 43
1792686826 48
1792686831 48
1792686836 48
1792686841 48
1792686846 48
1792686851 48
1792686856 48
1792686861 48
1792686866 48
1792686871 48
1792686876 48
1792686881 48
1792686886 43
1792686891 43
1792686896 43
```
</details>

---

