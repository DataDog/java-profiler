---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 00:58:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1788324830 94
1788324835 90
1788324840 90
1788324845 92
1788324850 92
1788324855 94
1788324860 94
1788324865 92
1788324870 92
1788324875 90
1788324880 90
1788324885 90
1788324890 90
1788324895 90
1788324900 88
1788324905 88
1788324910 88
1788324915 88
1788324920 92
1788324925 92
```
</details>

---

