---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:58:02 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 30-34 cores)</summary>

```
1794930721 34
1794930726 34
1794930731 34
1794930736 34
1794930741 34
1794930746 34
1794930751 34
1794930756 34
1794930761 34
1794930766 34
1794930771 34
1794930776 34
1794930781 34
1794930786 34
1794930791 34
1794930796 34
1794930801 34
1794930806 34
1794930811 34
1794930816 34
```
</details>

---

