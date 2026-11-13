---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 13:24:50 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794594100 51
1794594105 46
1794594110 46
1794594115 46
1794594120 46
1794594125 46
1794594130 46
1794594135 46
1794594140 46
1794594145 46
1794594150 46
1794594155 46
1794594160 46
1794594165 51
1794594170 51
1794594175 51
1794594180 51
1794594185 51
1794594190 51
1794594195 51
```
</details>

---

