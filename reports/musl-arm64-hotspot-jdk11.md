---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 09:18:49 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 918 |
| Sample Rate | 15.30/sec |
| Health Score | 956% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794492729 48
1794492734 48
1794492739 48
1794492744 48
1794492749 48
1794492754 48
1794492759 36
1794492764 36
1794492769 36
1794492774 36
1794492779 36
1794492784 36
1794492789 36
1794492794 36
1794492799 36
1794492804 36
1794492809 36
1794492814 36
1794492819 36
1794492824 36
```
</details>

---

