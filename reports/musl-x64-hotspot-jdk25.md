---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 08:51:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1787230078 92
1787230083 92
1787230088 92
1787230093 92
1787230098 92
1787230103 92
1787230108 92
1787230113 92
1787230118 92
1787230123 92
1787230128 94
1787230133 94
1787230138 94
1787230143 94
1787230148 94
1787230153 94
1787230158 94
1787230163 94
1787230168 96
1787230173 96
```
</details>

---

