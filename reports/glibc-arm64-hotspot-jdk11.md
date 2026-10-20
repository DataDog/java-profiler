---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 06:42:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1792492645 48
1792492650 48
1792492655 47
1792492660 47
1792492665 47
1792492670 47
1792492675 47
1792492680 47
1792492685 47
1792492690 47
1792492695 47
1792492700 47
1792492705 47
1792492710 47
1792492715 48
1792492720 48
1792492725 48
1792492730 48
1792492735 48
1792492740 48
```
</details>

---

