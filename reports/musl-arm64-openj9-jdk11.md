---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 03:28:11 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791530626 48
1791530631 48
1791530636 48
1791530641 48
1791530646 48
1791530651 48
1791530656 48
1791530661 48
1791530666 48
1791530671 48
1791530676 48
1791530681 48
1791530686 48
1791530691 48
1791530696 48
1791530701 48
1791530706 48
1791530711 48
1791530716 48
1791530721 48
```
</details>

---

