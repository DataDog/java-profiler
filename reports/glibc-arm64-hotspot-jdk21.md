---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 08:24:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (6 unique values: 20-45 cores)</summary>

```
1790770763 20
1790770768 20
1790770773 20
1790770778 20
1790770783 20
1790770788 20
1790770793 20
1790770798 20
1790770803 20
1790770808 20
1790770813 20
1790770818 30
1790770823 30
1790770828 39
1790770833 39
1790770838 39
1790770843 39
1790770848 36
1790770853 36
1790770858 45
```
</details>

---

