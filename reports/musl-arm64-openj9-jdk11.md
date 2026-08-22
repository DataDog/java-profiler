---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 15:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787426607 64
1787426612 64
1787426617 64
1787426622 64
1787426627 64
1787426632 64
1787426637 64
1787426642 64
1787426647 64
1787426652 64
1787426657 64
1787426662 64
1787426667 64
1787426672 64
1787426677 64
1787426682 64
1787426687 64
1787426692 64
1787426697 64
1787426702 64
```
</details>

---

