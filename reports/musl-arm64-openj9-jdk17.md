---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 01:03:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1791867567 16
1791867572 18
1791867577 18
1791867582 18
1791867587 18
1791867592 18
1791867597 18
1791867602 18
1791867607 18
1791867612 18
1791867617 18
1791867622 18
1791867627 18
1791867632 18
1791867637 18
1791867642 18
1791867647 18
1791867652 18
1791867657 18
1791867662 18
```
</details>

---

