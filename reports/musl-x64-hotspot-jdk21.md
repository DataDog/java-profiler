---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-08-18 05:22:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787044615 94
1787044620 94
1787044625 94
1787044630 94
1787044635 94
1787044640 94
1787044645 94
1787044650 94
1787044655 94
1787044660 94
1787044665 94
1787044670 94
1787044675 94
1787044680 94
1787044685 94
1787044690 94
1787044695 96
1787044700 96
1787044705 96
1787044710 96
```
</details>

---

