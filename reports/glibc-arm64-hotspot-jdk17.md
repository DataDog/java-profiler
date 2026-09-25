---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 00:58:48 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1790312086 22
1790312091 22
1790312096 22
1790312101 22
1790312106 22
1790312111 22
1790312116 22
1790312121 22
1790312126 22
1790312131 27
1790312136 27
1790312141 27
1790312146 27
1790312151 27
1790312156 27
1790312161 27
1790312166 27
1790312171 27
1790312176 27
1790312181 25
```
</details>

---

