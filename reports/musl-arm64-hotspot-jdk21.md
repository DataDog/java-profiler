---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 12:28:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1793812782 44
1793812788 44
1793812793 44
1793812798 44
1793812803 44
1793812808 44
1793812813 44
1793812818 49
1793812823 49
1793812828 44
1793812833 44
1793812838 44
1793812843 44
1793812848 44
1793812853 44
1793812858 44
1793812863 44
1793812868 44
1793812873 44
1793812878 44
```
</details>

---

