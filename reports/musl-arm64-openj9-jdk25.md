---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 13:49:23 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 9 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1792777515 48
1792777520 48
1792777525 48
1792777530 48
1792777535 48
1792777540 48
1792777545 59
1792777550 59
1792777555 64
1792777560 64
1792777565 64
1792777570 64
1792777575 64
1792777580 64
1792777585 64
1792777590 64
1792777595 64
1792777600 64
1792777605 64
1792777610 64
```
</details>

---

