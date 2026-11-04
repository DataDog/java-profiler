---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 12:28:11 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793812786 36
1793812791 36
1793812796 36
1793812801 36
1793812806 36
1793812811 36
1793812816 36
1793812821 36
1793812826 36
1793812831 36
1793812836 36
1793812841 36
1793812846 36
1793812851 36
1793812856 36
1793812861 36
1793812866 36
1793812871 36
1793812876 36
1793812881 36
```
</details>

---

