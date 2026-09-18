---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 05:01:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1789721716 19
1789721721 19
1789721726 19
1789721731 19
1789721736 19
1789721741 19
1789721746 19
1789721751 19
1789721756 19
1789721761 19
1789721766 19
1789721771 19
1789721776 19
1789721781 24
1789721786 24
1789721791 24
1789721796 24
1789721801 24
1789721806 24
1789721811 24
```
</details>

---

