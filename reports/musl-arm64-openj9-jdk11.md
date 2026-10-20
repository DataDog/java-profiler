---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 12:18:20 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1792512743 48
1792512748 48
1792512753 48
1792512758 48
1792512763 48
1792512768 48
1792512773 48
1792512778 48
1792512783 48
1792512788 48
1792512793 48
1792512798 48
1792512803 48
1792512808 48
1792512813 48
1792512818 48
1792512823 48
1792512828 48
1792512833 48
1792512838 48
```
</details>

---

