---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 05:26:29 EDT

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
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787044753 64
1787044758 64
1787044763 64
1787044768 64
1787044773 64
1787044778 64
1787044783 64
1787044788 64
1787044793 64
1787044798 64
1787044803 64
1787044808 64
1787044813 64
1787044818 64
1787044823 64
1787044828 64
1787044833 64
1787044838 64
1787044843 64
1787044848 64
```
</details>

---

