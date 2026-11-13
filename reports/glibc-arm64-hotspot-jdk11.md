---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:27:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794572497 48
1794572502 48
1794572507 48
1794572512 48
1794572517 48
1794572522 48
1794572527 48
1794572532 48
1794572537 48
1794572542 48
1794572547 48
1794572552 48
1794572557 48
1794572562 48
1794572567 48
1794572572 48
1794572577 48
1794572582 48
1794572587 48
1794572592 48
```
</details>

---

