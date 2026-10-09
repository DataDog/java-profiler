---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 07:07:00 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1791543750 40
1791543755 40
1791543760 40
1791543765 48
1791543770 48
1791543775 48
1791543780 48
1791543785 48
1791543790 48
1791543795 43
1791543800 43
1791543805 43
1791543810 43
1791543815 43
1791543820 43
1791543825 43
1791543830 43
1791543835 43
1791543840 43
1791543845 43
```
</details>

---

