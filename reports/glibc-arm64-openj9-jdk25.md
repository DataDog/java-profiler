---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 19:52:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1793926150 37
1793926155 42
1793926160 42
1793926165 42
1793926170 42
1793926175 42
1793926180 42
1793926185 42
1793926190 42
1793926195 42
1793926200 42
1793926205 42
1793926210 42
1793926215 42
1793926220 42
1793926225 42
1793926230 42
1793926235 42
1793926240 42
1793926245 42
```
</details>

---

