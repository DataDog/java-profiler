---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:36:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 28-33 cores)</summary>

```
1795620719 33
1795620724 33
1795620729 33
1795620734 33
1795620739 33
1795620744 33
1795620749 33
1795620754 33
1795620759 33
1795620764 33
1795620769 31
1795620774 31
1795620779 31
1795620784 31
1795620789 31
1795620794 31
1795620799 31
1795620804 31
1795620809 33
1795620814 33
```
</details>

---

