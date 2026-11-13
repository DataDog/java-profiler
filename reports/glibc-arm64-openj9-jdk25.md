---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:27:30 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1794572576 31
1794572581 31
1794572586 31
1794572591 31
1794572596 31
1794572601 31
1794572606 31
1794572612 31
1794572617 31
1794572622 31
1794572627 31
1794572632 31
1794572637 31
1794572642 31
1794572647 31
1794572652 31
1794572657 31
1794572662 31
1794572667 31
1794572672 31
```
</details>

---

