---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 17:52:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 16 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1792532772 64
1792532777 64
1792532782 64
1792532787 64
1792532792 64
1792532797 64
1792532802 64
1792532807 64
1792532812 64
1792532817 64
1792532822 64
1792532827 64
1792532832 64
1792532837 64
1792532842 64
1792532847 64
1792532852 64
1792532857 64
1792532862 64
1792532867 64
```
</details>

---

