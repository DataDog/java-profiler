---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:01:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 8 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795618592 64
1795618597 64
1795618602 64
1795618607 64
1795618612 64
1795618617 64
1795618622 64
1795618627 64
1795618632 64
1795618637 64
1795618642 64
1795618647 64
1795618652 64
1795618657 62
1795618662 62
1795618667 62
1795618672 62
1795618677 62
1795618682 62
1795618687 62
```
</details>

---

