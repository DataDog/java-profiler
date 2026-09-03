---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 15:56:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 20-32 cores)</summary>

```
1788465047 27
1788465052 27
1788465057 27
1788465062 27
1788465067 27
1788465072 27
1788465077 27
1788465082 27
1788465087 27
1788465092 27
1788465097 27
1788465102 27
1788465107 32
1788465112 32
1788465117 32
1788465122 32
1788465127 32
1788465132 32
1788465137 32
1788465142 32
```
</details>

---

