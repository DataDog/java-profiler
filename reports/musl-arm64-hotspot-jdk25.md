---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 12:28:13 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 10-10 cores)</summary>

```
1793812789 10
1793812794 10
1793812799 10
1793812804 10
1793812809 10
1793812814 10
1793812819 10
1793812824 10
1793812829 10
1793812834 10
1793812839 10
1793812844 10
1793812849 10
1793812854 10
1793812859 10
1793812864 10
1793812869 10
1793812874 10
1793812880 10
1793812885 10
```
</details>

---

