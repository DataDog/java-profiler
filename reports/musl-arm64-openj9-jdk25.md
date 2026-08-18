---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 05:22:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787044631 48
1787044636 48
1787044641 48
1787044646 48
1787044651 48
1787044656 48
1787044661 48
1787044666 48
1787044671 48
1787044676 48
1787044681 48
1787044686 48
1787044691 48
1787044696 48
1787044701 48
1787044706 48
1787044711 48
1787044716 43
1787044721 43
1787044726 43
```
</details>

---

