---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 12:22:24 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792426680 64
1792426685 64
1792426690 64
1792426695 64
1792426700 64
1792426705 64
1792426710 64
1792426715 64
1792426720 64
1792426725 64
1792426730 64
1792426735 64
1792426740 64
1792426745 64
1792426750 64
1792426755 64
1792426760 64
1792426765 64
1792426770 64
1792426775 64
```
</details>

---

